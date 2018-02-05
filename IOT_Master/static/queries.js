let value = "";
let stopUpdate = false;

$(document).ready(function () {
    //renderGUI();
    let intervalPeriod = 1000;

    setInterval(function () {

        renderGUI();

    }, intervalPeriod);


    $(document).on('click', '.htmlFlipper', function (e) {

        console.log(e.target.id);

        var url = "/flipValue/" + e.target.id;
        console.log("Here");

        $.ajax({
            type: 'GET',
            url: url,
            success: function (result) {
                console.log(result);
            }
        });

    });


});


function renderGUI() {
    if(!stopUpdate){
            $.ajax({
            type: 'POST',
            url: 'listOfVariables',
            success: function (result) {
                let html = '';

                html += '<table>' +
                        '<tr>' +
                        '   <th>Namn</th>' +
                        '   <th>Värde</th>' +
                        '</tr>';

                for (currentId in result) {

                    //console.log(currentId);

                    html += '<tr>' +
                            '   <td> ' + result[currentId]['name'] + '</td>' +
                            '   <td>';


                    if(result[currentId]["type"] === "bool"){

                        html += '<button type="button" class="htmlFlipper" id="' + currentId +'">' + boolToString(result[currentId]['value']) + '</button>';
                    }
                    else if(result[currentId]["type"] === "percent"){

                        html += '<input type="text" ' +
                                'id="' + currentId + '" ' +
                                'onfocus="stop()"' +
                                'placeholder="' + result[currentId]["value"] + '" ' +
                                'onkeydown="return checkChar(event, this.id); " ' +
                                '">';


                        if(stopUpdate){
                            break;
                        }
                    }
                    else{

                        html += '<p id=staticVal >' + result[currentId]["value"] + '</p>';
                    }

                    html += '</td> </tr>';

                }

                html += '</table>';

                $('#units').html(html);

                }
            });
        }
}

function flipValue(result, id) {
    var url = "/flipValue/id=" + id + "&o=write&v";

    if(result[id]['value'] === '0'){
        url += '1'
    }
    else if(result[id]['value'] === '1'){
        url += '0'
    }
    else{
        return
    }

    $.ajax({
        type: 'POST',
        url: url,
        success: function () {
            console.log("Wrote " + url)
        }
    })
}

function setValue(id, value){
    var url = "/internalVariable/id=" + id + "&o=write&v=" + value;

    console.log(url);
    $.ajax({
        type: 'POST',
        url: url,
        success: function () {
            console.log("Wrote " + url)
        }
    })
}

function stop() {
    stopUpdate = true;

    console.log("Stop");

}

function start() {
    stopUpdate = false;
    console.log("Start");
}

function printStuff() {
    console.log("Ompa lompa didilidoo")
}

function updateValue(id) {
    console.log("Id in updateValue: " + id);
    let value = document.getElementById(id).value;
    start();
    console.log(value)

    if(value === ""){

    }
    else if(isNaN(parseInt(value))){

    }
    else if(parseInt(value) > 100 || parseInt(value) < 0){

    }
    else{
        setValue(id, value);
    }


}

function checkChar(e, id) {
    if(e.keyCode == 13){
        updateValue(id);

    }
}

function boolToString(boolean){
    if(boolean === '0'){
        return "OFF";
    }
    else if(boolean === '1'){
        return "ON";
    }
    else
        return "";
}
