def parseVariables(variables):          #Takes a string and returns a dict of dicts
    variables = variables.split('&')    #Splits the variables string at every different operator
    output = dict()

    for currentVariable in variables:
        seperatedVal = currentVariable.split('=')   #Splits the operator and the value

        if len(seperatedVal) >= 2:
            output[seperatedVal[0]] = seperatedVal[1]   #Adds the value to an operator-instance in the output-dict

            print("Parsed to %s = %s"%(seperatedVal[0], seperatedVal[1]))

        else:
            print("Could not parse" + currentVariable)


    return output       #Returns the resulting dict