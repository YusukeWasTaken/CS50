import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from functions import apology, login_required


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")

@app.route("/")
def index():
    # TODO
    return render_template("homepage.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    # Forget any user_id
    session.clear()

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            return apology("Must provide username")

        elif not password:
            return apology("Must return password")

        rows = db.execute("SELECT * FROM users WHERE username = :username",
        username = username)

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("Invalid username or password")

        session["user_id"] = rows[0]["id"]

        return redirect("/")
    
    else:
        return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Must provide username")

        elif not password or not confirmation:
            return apology("Must provide password and confirmation")

        if password != confirmation:
            return apology("Password and confirmation do not match")

        pwhash = generate_password_hash(password)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username = username)
        if len(rows) != 0:
            return apology("Username as been already taken")
        
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, pwhash)
        Id = db.execute("SELECT id FROM users WHERE username = :username", username = username)
        db.execute("INSERT INTO content (id) VALUES (?)", Id[0]["id"])

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/mal", methods=["GET", "POST"])
@login_required
def mal():
    
    if request.method == "POST":
        alist = request.form.get("mal")

        if not alist:
            return apology("Must provide you MyAnimeList link")

        db.execute("UPDATE content set mal = :mal WHERE id = :id",mal = alist, id=session["user_id"])

        return redirect("/")
    else:
        exist = db.execute("SELECT mal FROM content WHERE id = :id", id=session["user_id"])
        if exist[0]["mal"] == None:
            return render_template("mal.html")
        else:
            return redirect(exist[0]["mal"])
    
@app.route("/imdb", methods=["GET", "POST"])
@login_required
def imdb():
    
    if request.method == "POST":
        alist = request.form.get("imdb")

        if not alist:
            return apology("Must provide you imdb link")

        db.execute("UPDATE content set imdb = :imdb WHERE id = :id",imdb = alist, id=session["user_id"])

        return redirect("/")
    else:
        exist = db.execute("SELECT imdb FROM content WHERE id = :id", id=session["user_id"])
        if exist[0]["imdb"] == None:
            return render_template("imdb.html")
        else:
            return redirect(exist[0]["imdb"])

@app.route("/steam", methods=["GET", "POST"])
@login_required
def steam():
    
    if request.method == "POST":
        alist = request.form.get("steam")

        if not alist:
            return apology("Must provide you steam link")

        db.execute("UPDATE content set steam = :steam WHERE id = :id",steam = alist, id=session["user_id"])

        return redirect("/")
    else:
        exist = db.execute("SELECT steam FROM content WHERE id = :id", id=session["user_id"])
        if exist[0]["steam"] == None:
            return render_template("steam.html")
        else:
            return redirect(exist[0]["steam"])

@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():

    if request.method == "POST":
        cpassword = request.form.get("cpassword")
        npassword = request.form.get("npassword")
        confirmation = request.form.get("confirmation")
        mal = request.form.get("mal")
        imdb = request.form.get("imdb")
        steam = request.form.get("steam")

        if cpassword and npassword == confirmation:
            db.execute("UPDATE users set hash = :hash WHERE id = :id", hash=generate_password_hash(npassword), id=session["user_id"])
        elif not npassword and not cpassword and not confirmation:
            # links
            if mal:
                db.execute("UPDATE content set mal = :mal WHERE id = :id", mal=mal, id=session["user_id"])
            if imdb:
                db.execute("UPDATE content set imdb = :imdb WHERE id = :id", imdb=imdb, id=session["user_id"])
            if steam:
                db.execute("UPDATE content set steam = :steam WHERE id = :id", steam=steam, id=session["user_id"])
        else:
            return apology("You must enter your current and new password! The new one and the confirmation must also match!")
        return redirect("/")
    else:
        rows = db.execute("SELECT * FROM content WHERE id = :id", id = session["user_id"])
        mal = rows[0]["mal"]
        imdb = rows[0]["imdb"]
        steam = rows[0]["steam"]
        return render_template("settings.html", mal=mal,imdb=imdb,steam=steam)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)