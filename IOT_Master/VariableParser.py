def parseVariable(variables):
    output = parseVariable(variables)

    print("id=%s, operation=%s, value=%s" % (output.get("id"), output.get("o"), output.get("v")))

def parseVariables(variables):
    variables = variables.split('&')
    output = dict()

    for currentVariable in variables:
        seperatedVal = currentVariable.split('=')

        if len(seperatedVal) >= 2:
            output[seperatedVal[0]] = seperatedVal[1]

            print("Parsed to %s = %s"%(seperatedVal[0], seperatedVal[1]))

        else:
            print("Could not parse" + currentVariable)


    return output