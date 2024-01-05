from flask import Flask, render_template, request, render_template_string

app = Flask(__name__, static_url_path="/assets", static_folder="assets")
app.config["FLAG"] = "You're at the right path, but no. The flag is not here."
app.config["USERNAME"] = "theflash2k"
app.config["PASSWORD"] = "6s1251l7sj1"

@app.route("/")
def index():
    return render_template("index.html")

@app.errorhandler(404)
def not_found(error):
    endpoint = request.full_path[:-1] # Removing the ?
    html = """<!DOCTYPE html>
<html>
<!-- Default `python -m http.server` error page -->
    <head>
        <meta http-equiv="Content-Type" content="text/html;charset=utf-8">
        <title>Error response</title>
    </head>
    <body>
        <h1>Error response</h1>
        <p>Error code: 404</p>
        <p>Message: {endpoint} not found.</p>
        <p>Error code explanation: HTTPStatus.NOT_FOUND - Nothing matches the given URI.</p>
    </body>
</html>
""".format(endpoint=endpoint)

    return render_template_string(html), 404

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)