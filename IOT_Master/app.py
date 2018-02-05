import flask
import time
import os
import socket
import Parsing

app = flask.Flask(__name__)

@app.route("/variable/<string:variables>", methods=["GET"])     #Used by other (none-graphic) units to get/set a variable as a string
def variables(variables):
    return Parsing.variable(variables)

@app.route("/internalVariable/<string:variables>", methods=["POST"])    #Used the same as before, but for internal variable-handling
def internalVariables(variables):
    return Parsing.variable(variables)


@app.route("/getTime")
def getTime():
    return flask.render_template_string(str(int(time.time())))          #Returns the current timestamp, for units

@app.route("/listOfVariables", methods=['POST'])        #Internal loading of a jsonified version of the dict of variables.
def listOfVariables():                                  #Is used to relode the GUI
    return flask.jsonify(Parsing.load_file())


@app.route('/')
def home():
    return flask.render_template("home.html")           #Loades the GUI

@app.route('/flipValue/<string:id>', methods=['GET'])   #A version of the variables function that flips a boolean value
def flip(id):
    if not Parsing.flip(id):
        print("Could not flip unit " + id)
        return flask.jsonify("Failed.")

    return flask.jsonify("Susess.")





if __name__ == '__main__':  # Ifall __name__ är __main__ betyder det att det är scriptet som ska exicueras
    app.run(debug=True, host=socket.gethostbyname(socket.gethostname()))  # Startar app med debug-läge
