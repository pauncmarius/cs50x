import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Figure out how many shares of each symbol the user currently owns.
    # Purchases add shares, and sales subtract them.
    rows = db.execute(
        """
        SELECT symbol,
               SUM(CASE
                   WHEN action = 'buy' THEN shares
                   WHEN action = 'sell' THEN -shares
               END) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(CASE
                   WHEN action = 'buy' THEN shares
                   WHEN action = 'sell' THEN -shares
               END) > 0
        """,
        session["user_id"]
    )

    stocks = []
    stock_total = 0

    # For each symbol, check the current market price and calculate the holding value.
    for row in rows:
        stock = lookup(row["symbol"])

        if stock is not None:
            total = row["shares"] * stock["price"]

            stocks.append({
                "symbol": row["symbol"],
                "name": stock["name"],
                "shares": row["shares"],
                "price": stock["price"],
                "total": total
            })

            stock_total += total

    # Check how much cash the user has left in their account.
    cash_rows = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        session["user_id"]
    )
    cash = cash_rows[0]["cash"]

    # Grand total: cold hard cash plus the total value of all stocks.
    grand_total = cash + stock_total

    return render_template(
        "index.html",
        stocks=stocks,
        cash=cash,
        grand_total=grand_total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # First time visiting? Show the buy form.
    if request.method == "GET":
        return render_template("buy.html")

    # Grab what they filled in
    symbol = request.form.get("symbol")
    shares_text = request.form.get("shares")

    # Make sure they actually provided the required info
    if not symbol:
        return apology("must provide symbol")

    if not shares_text:
        return apology("must provide number of shares")

    try:
        shares = int(shares_text)
    except ValueError:
        return apology("shares must be a whole number")

    if shares < 1:
        return apology("shares must be at least 1")

    # Look up the stock info
    stock = lookup(symbol)

    if stock is None:
        return apology("invalid symbol")

    # Check if they've got enough cash in their pocket for this purchase
    rows = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        session["user_id"]
    )
    cash = rows[0]["cash"]
    total_cost = shares * stock["price"]

    if total_cost > cash:
        return apology("not enough cash")

    # Deduct the total cost from their balance
    db.execute(
        "UPDATE users SET cash = cash - ? WHERE id = ?",
        total_cost,
        session["user_id"]
    )

    # Save the transaction in the books
    db.execute(
        """
        INSERT INTO transactions (user_id, symbol, shares, price, action)
        VALUES (?, ?, ?, ?, ?)
        """,
        session["user_id"],
        stock["symbol"],
        shares,
        stock["price"],
        "buy"
    )

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Pull up all user transactions, newest ones first
    rows = db.execute(
        """
        SELECT symbol, shares, price, action, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC, id DESC
        """,
        session["user_id"]
    )

    transactions = []

    # Calculate the total value for each transaction line
    for row in rows:
        transactions.append({
            "symbol": row["symbol"],
            "shares": row["shares"],
            "price": row["price"],
            "action": row["action"],
            "transacted": row["transacted"],
            "total": row["shares"] * row["price"]
        })

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Send them back to the login page
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # First time visiting? Show the quote form.
    if request.method == "GET":
        return render_template("quote.html")

    # When they submit the form, grab the symbol
    symbol = request.form.get("symbol")

    if not symbol:
        return apology("must provide symbol")

    # lookup is the helper function provided in helpers.py
    stock = lookup(symbol)

    if stock is None:
        return apology("invalid symbol")

    # Show the results page
    return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Just opening the page? Show the registration form.
    if request.method == "GET":
        return render_template("register.html")

    # Grab what they filled in
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    # Make sure everything was filled out correctly
    if not username:
        return apology("must provide username")

    if not password:
        return apology("must provide password")

    if password != confirmation:
        return apology("passwords do not match")

    # Check if this username is already taken
    rows = db.execute(
        "SELECT * FROM users WHERE username = ?",
        username
    )

    if len(rows) > 0:
        return apology("username already exists")

    # Never store raw passwords; save their secure hash instead
    password_hash = generate_password_hash(password)

    db.execute(
        "INSERT INTO users (username, hash) VALUES (?, ?)",
        username,
        password_hash
    )

    # Registration done, send them over to log in
    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Calculate current holdings: buys add up, sells subtract.
    holdings = db.execute(
        """
        SELECT symbol,
               SUM(CASE
                   WHEN action = 'buy' THEN shares
                   WHEN action = 'sell' THEN -shares
               END) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(CASE
                   WHEN action = 'buy' THEN shares
                   WHEN action = 'sell' THEN -shares
               END) > 0
        """,
        session["user_id"]
    )

    # First time visiting? Show the sell form preloaded with their stocks.
    if request.method == "GET":
        return render_template("sell.html", stocks=holdings)

    symbol = request.form.get("symbol")
    shares_text = request.form.get("shares")

    if not symbol:
        return apology("must select a stock")

    if not shares_text:
        return apology("must provide number of shares")

    try:
        shares = int(shares_text)
    except ValueError:
        return apology("shares must be a whole number")

    if shares < 1:
        return apology("shares must be at least 1")

    # Double-check how many shares of this specific symbol the user actually owns.
    owned_rows = db.execute(
        """
        SELECT SUM(CASE
                   WHEN action = 'buy' THEN shares
                   WHEN action = 'sell' THEN -shares
               END) AS shares
        FROM transactions
        WHERE user_id = ? AND symbol = ?
        """,
        session["user_id"],
        symbol
    )

    owned = owned_rows[0]["shares"] or 0

    if owned == 0:
        return apology("you do not own this stock")

    if shares > owned:
        return apology("you do not own that many shares")

    stock = lookup(symbol)

    if stock is None:
        return apology("invalid symbol")

    # Add the cash made from the sale back to their balance.
    proceeds = shares * stock["price"]

    db.execute(
        "UPDATE users SET cash = cash + ? WHERE id = ?",
        proceeds,
        session["user_id"]
    )

    # Record the sale; shares stay positive, but action='sell' handles subtraction in logic.
    db.execute(
        """
        INSERT INTO transactions (user_id, symbol, shares, price, action)
        VALUES (?, ?, ?, ?, ?)
        """,
        session["user_id"],
        symbol,
        shares,
        stock["price"],
        "sell"
    )

    return redirect("/")


@app.route("/profile", methods=["GET", "POST"])
@login_required
def profile():
    """Let the user change their username and password."""

    user_id = session["user_id"]

    rows = db.execute(
        "SELECT username, hash FROM users WHERE id = ?",
        user_id
    )

    # If the user somehow vanished from the database, log them out.
    if len(rows) != 1:
        session.clear()
        return redirect("/login")

    user = rows[0]

    # When opening the page, show their current username.
    if request.method == "GET":
        return render_template("profile.html", username=user["username"])

    # Grab what they typed into the form.
    username = request.form.get("username", "").strip()
    current_password = request.form.get("current_password", "")
    new_password = request.form.get("new_password", "")
    confirmation = request.form.get("confirmation", "")

    # Make sure all required fields are filled out.
    if not username:
        return apology("must provide username")

    if not current_password:
        return apology("must provide current password")

    # Verify their current password before letting them make any profile changes.
    if not check_password_hash(user["hash"], current_password):
        return apology("incorrect current password")

    # If they're trying to set a new password, make sure the confirmation matches.
    if new_password != confirmation:
        return apology("new passwords do not match")

    # Make sure no other user has already taken that new username.
    existing_users = db.execute(
        "SELECT id FROM users WHERE username = ? AND id != ?",
        username,
        user_id
    )

    if len(existing_users) > 0:
        return apology("username already taken")

    # Save the new username and password (if they provided one).
    if new_password:
        new_hash = generate_password_hash(new_password)

        db.execute(
            "UPDATE users SET username = ?, hash = ? WHERE id = ?",
            username,
            new_hash,
            user_id
        )
    else:
        # A new password is optional, so we can just update the username alone.
        db.execute(
            "UPDATE users SET username = ? WHERE id = ?",
            username,
            user_id
        )

    flash("Profile updated successfully!")
    return redirect("/profile")
