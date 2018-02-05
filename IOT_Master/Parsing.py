import flask
import os


def variable(variables):
    variables = variables.split('&')
    output = dict()

    for currentVariable in variables:
        seperatedVal = currentVariable.split('=')

        if len(seperatedVal) >= 2:
            output[seperatedVal[0]] = seperatedVal[1]

        else:
            print("Could not parse" + currentVariable)

            #
            #
            #

    dictOfUnits = load_file()

    if output.get("id") not in dictOfUnits:
        print("Could not find unit with id '%s'" % output.get("id"))

        return flask.render_template_string('Undefined id')

    elif output.get("o") == "write" and output.get("v") is not None:
        dictOfUnits[output.get("id")]["value"] = output.get("v")

    elif output.get("o") == "write":
        return flask.render_template_string('Undefined replacement value')

    elif output.get("o") == "read":
        pass

    else:
        print("There is no operator named '%s'" % output.get("o"))
        return flask.render_template_string('Undefined operator')

    save_file(dictOfUnits)
    return flask.render_template_string(dictOfUnits[output.get("id")]["value"])


def load_file():
    filepath = os.getcwd() + "/variables.txt"
    output = dict()

    try:
        file = open(filepath, 'r')

    except IOError:
        print("Could not open file. " + filepath)
        return

    line = file.readline()

    while line != '':

        line = line.split("=")

        id = "None"
        value = "None"
        name = "None"
        type = "None"

        try:
            id = line[0]
            name = line[1]
            type = line[2]
            value = line[3][:-1]

            output[id] = {"name": name, "type": type, "value": value}

        except IndexError:
            print("Could not create index. id=%s, name=%s, type=%s value=%s" % (id, name, type, value))

        line = file.readline()

    return output


def save_file(inputDict):
    filepath = os.getcwd() + "/variables.txt"

    try:
        file = open(filepath, 'w')

    except IOError:
        print("Could not open file. " + filepath)
        return False

    for instance in inputDict:
        file.write(instance + '=' +
                   inputDict[instance]["name"] + '=' +
                   inputDict[instance]["type"] + '=' +
                   inputDict[instance]["value"] + '\n')

    return True

def flip(id):

    dictOfUnits = load_file()

    if id not in dictOfUnits:
        print("Could not find unit with id '%s'" % id)

        return False

    elif dictOfUnits[id]["type"] != "bool":
        print("This id is not a bool; " + id)

        return False

    print("value = " + dictOfUnits[id]["value"])

    if dictOfUnits[id]["value"] == "0":
        dictOfUnits[id]["value"] = "1"

    elif dictOfUnits[id]["value"] == "1":
        dictOfUnits[id]["value"] = "0"

    else:
        return False

    save_file(dictOfUnits)

    return True
