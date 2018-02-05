import flask
import os


def variable(variables):                #Parses a command, loads a file with data, changes the file, saves it and return the value
    variables = variables.split('&')
    output = dict()

    for currentVariable in variables:
        seperatedVal = currentVariable.split('=')       #Parses the command from the url

        if len(seperatedVal) >= 2:
            output[seperatedVal[0]] = seperatedVal[1]

        else:
            print("Could not parse" + currentVariable)

    dictOfUnits = load_file()       #Loades the file to dictOfUnits, a dict containing dicts of different variables

    if output.get("id") not in dictOfUnits:
        print("Could not find unit with id '%s'" % output.get("id"))    #Checks the existans of the id in the list

        return flask.render_template_string('Undefined id')

    elif output.get("o") == "write" and output.get("v") is not None:    #Writes a variable in the list to a value from output from the parsing of the variables,
        dictOfUnits[output.get("id")]["value"] = output.get("v")        #as long as there is a value v

    elif output.get("o") == "write":
        return flask.render_template_string('Undefined replacement value')  #Error when there is no value v

    elif output.get("o") == "read": #Passes to the return statement
        pass

    else:
        print("There is no operator named '%s'" % output.get("o"))  #Prints an error in the consol, and returns 'Undefined operator'
        return flask.render_template_string('Undefined operator')

    save_file(dictOfUnits)
    return flask.render_template_string(dictOfUnits[output.get("id")]["value"])     #Saves the dictOfUnits and returns a rendered string with the value


def load_file():                                #Loades a file and returns a dict of dicts containing all the variables
    filepath = os.getcwd() + "/variables.txt"
    output = dict()

    try:
        file = open(filepath, 'r')              #Tries to open the file

    except IOError:
        print("Could not open file. " + filepath)
        return

    line = file.readline()

    while line != '':           #Tries to add the variables from the file to the dict

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

    return output       #Returns the dict of dicts


def save_file(inputDict):               #Saves the inputDict to a file
    filepath = os.getcwd() + "/variables.txt"

    try:
        file = open(filepath, 'w')

    except IOError:
        print("Could not open file. " + filepath)       #Tries to open the file
        return False

    for instance in inputDict:
        file.write(instance + '=' +
                   inputDict[instance]["name"] + '=' +
                   inputDict[instance]["type"] + '=' +      #Writes every instance as instance=name=type=value\n
                   inputDict[instance]["value"] + '\n')

    return True

def flip(id):

    dictOfUnits = load_file()   #Loades the dictOfUnits

    if id not in dictOfUnits:
        print("Could not find unit with id '%s'" % id)      #Checks for the id in the dictOfUnits

        return False

    elif dictOfUnits[id]["type"] != "bool":
        print("This id is not a bool; " + id)       #Makes sure that the type of the variable is bool

        return False

    print("value = " + dictOfUnits[id]["value"])

    if dictOfUnits[id]["value"] == "0":         #Flipps the boolean value
        dictOfUnits[id]["value"] = "1"

    elif dictOfUnits[id]["value"] == "1":
        dictOfUnits[id]["value"] = "0"

    else:
        return False

    save_file(dictOfUnits)          #Saves the file

    return True
