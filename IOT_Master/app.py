import flask
import time
import os
import socket
import Parsing

app = flask.Flask(__name__)

@app.route("/variable/<string:variables>", methods=["GET"])
def variables(variables):
    return Parsing.variable(variables)

@app.route("/internalVariable/<string:variables>", methods=["POST"])
def internalVariables(variables):
    return Parsing.variable(variables)


@app.route("/getTime")
def getTime():
    return flask.render_template_string(str(int(time.time())))
    #return render_template_string("1515880797")

@app.route("/listOfVariables", methods=['POST'])
def listOfVariables():
    return flask.jsonify(Parsing.load_file())


@app.route('/')
def home():
    return flask.render_template("home.html")

@app.route('/flipValue/<string:id>', methods=['GET'])
def flip(id):
    if not Parsing.flip(id):
        print("Could not flip unit " + id)
        return flask.jsonify("Failed.")

    return flask.jsonify("Susess.")





if __name__ == '__main__':  # Ifall __name__ är __main__ betyder det att det är scriptet som ska exicueras
    app.run(debug=True, host=socket.gethostbyname(socket.gethostname()))  # Startar app med debug-läge
