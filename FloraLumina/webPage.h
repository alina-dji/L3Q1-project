#ifndef WEB_PAGE_H
#define WEB_PAGE_H

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Flora Lumina</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Abel&family=Dosis:wght@200..800&family=Source+Code+Pro:ital,wght@0,200..900;1,200..900&display=swap');
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: "Source Code Pro", monospace;
            background-color: black;
            color: whitesmoke;
        }
        h1 {
            margin-top: 2%;
            text-align: center;
        }
        .main {
            padding: 5%;
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        .motor-light {
            width: 100%;
            margin-bottom: 7%;
        }
        .color {
            margin-bottom: 8%;
        }
        .motor {
            margin-bottom: 4%;
        }
        .motor-slider {
            display: flex;
            justify-content: space-around;
        }
        .slider.label {
            width: 20%;
            margin-right: 1rem;
        }
        .slider {
            width: 50%;
        }
        input {
            appearance: none;
            height: 5px;
            border-radius: 10px;
            width: 80%;
        }
        select {
            background-color: rgb(46, 46, 46);
            color: whitesmoke;
            padding: 2%;
            border: none;
            border-radius: 20px;
            width: 100%;
            font-family: "Source Code Pro", monospace;
            margin-top: 1%;
            margin-bottom: 1%;
        }
        .motor {
            width: 100%;
            display: flex;
            flex-direction: column;
        }
        .modes {
            width: 100%;
            margin-bottom: 2%;
            display: flex;
            flex-direction: column;
            align-items: center;
        }
        .weather-station {
            width: 100%;
            border: solid 1px whitesmoke;
            border-radius: 10px;
            padding: 2%;
            display: flex;
            flex-direction: column;
        }
        @media (min-width: 700px) {
            h1 {
                font-size: 2.5rem;
            }
            .main {
                display: flex;
                flex-direction: row;
                justify-content: space-evenly;
            }
            .color {
                width: 30%;
                display: flex;
                flex-direction: column;
                /* background-color: blue; */
                align-items: center;
            }
            .motor-light {
                width: 30%;
                /* background-color: blueviolet; */
            }
            .weather-station {
                width: 30%;
                /* background-color: brown; */
                margin-bottom: 6%;
            }
        }
    </style>
</head>
<body>
    <h1>Flora Lumina</h1>
    <div class="main">
        <div class="color">
            <div class="color-picker"></div>
            <div id="color-picker"></div>
        </div>
        <div class="motor-light">
            <div class="modes">
                <select name="light-modes" id="light-mode-select">
                    <option value="">Light mode</option>
                    <option value="staticRainbow">Static Rainbow</option>
                    <option value="rainbow">Rainbow</option>
                    <option value="confetti">Confetti</option>
                    <option value="heartBeat">Heart Beat</option>
                    <option value="soundReactive">Sound Reactive</option>
                </select>
                <select name="flower-modes" id="flower-mode-select">
                    <option value="">Automatic mode</option>
                    <option value="distanceReactive">Distance reactive Mode</option>
                    <option value="lightTemperature">Light based on temperature</option>
                    <option value="lifeCycle">Life Cycle</option>
                    <option value="positionTemperature">Position based on temperature</option>
                    <option value="positionHumidity">Position based on humidity</option>
                </select>
            </div>
            <div class="motor">
                <div class="motor-slider position">
                    <span class="slider label">Position</span>
                    <span class="slider">
                        <input type="range" min="0" max="100" id="motor-position" name="motor" onchange="positionvalue.value=value"/>
                        <output id="positionvalue">50</output>
                    </span>
                </div>
                <div class="motor-slider speed">
                    <span class="slider label">Speed</span>
                    <span class="slider">
                        <input type = "range" min="0" max="100" id="motor-speed" name="motor" onchange="speedvalue.value=value"/>
                        <output id="speedvalue">50</output>
                    </span>
                </div>
            </div>
        </div>
        <div class="weather-station">
            <span class="label" id="luminosity">Luminosity: lux</span>
            <span class="label" id="temperature">Temperature: °C</span>
            <span class="label" id="humidity">Humidity: %</span>
            <span class="label" id="distance">Distance: mm</span>
        </div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/@jaames/iro@5"></script>

    <script>
        // Setting light color
        const colorPicker = new iro.ColorPicker("#color-picker", {width:240});
        colorPicker.on('color:change', function(color) {
            console.log(color.hexString);
            var hexColor = color.hexString;
            hexColor = hexColor.replace("#", "");
            var url = "/setColor?color=" + hexColor;
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("color value sent to wemos");
                    console.log(color.hexString);
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        });

        // Setting light mode
        var lightModeMenu = document.getElementById("light-mode-select");
        lightModeMenu.addEventListener("change", function() {
            var lightMode = lightModeMenu.value;
            var url = "/setLightMode?lightMode=" + lightMode;
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log(lightMode);
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        });

        // Setting flower mode
        var flowerModeMenu = document.getElementById("flower-mode-select");
        flowerModeMenu.addEventListener("change", function() {
            var flowerMode = flowerModeMenu.value;
            var url = "/setFlowerMode?flowerMode=" + flowerMode;
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log(flowerMode);
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        });

        // Setting motor openning position
        var motorPositionSlider = document.getElementById("motor-position");
        motorPositionSlider.addEventListener("change", function() {
            var motorPositionValue = motorPositionSlider.value;
            var url = "/setMotorPosition?motorPosition=" + motorPositionValue;
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log(motorPositionValue);
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        });

        // Setting motor speed
        var motorSpeedSlider = document.getElementById("motor-speed");
        motorSpeedSlider.addEventListener("change", function() {
            var motorSpeedValue = motorSpeedSlider.value;
            var url = "/setMotorSpeed?motorSpeed=" + motorSpeedValue;
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log(motorSpeedValue);
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        });

        // Displaying sensors data
        var luminosity = document.getElementById("luminosity");
        var temperature = document.getElementById("temperature");
        var humidity = document.getElementById("humidity");
        var pressure = document.getElementById("pressure");
        var distance = document.getElementById("distance");
        function getLuminosityData() {
            var url = "/getLuminosityData";
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("getting luminosity data");
                    luminosity.innerHTML = "Luminosity: " + xhr.responseText + " lux";
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        }
        function getTemperatureData() {
            var url = "/getTemperatureData";
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("getting temperature data");
                    temperature.innerHTML = "Temperature: " + xhr.responseText + "°C";
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        }
        function getHumidityData() {
            var url = "/getHumidityData";
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("getting humidity data");
                    humidity.innerHTML = "Humidity: " + xhr.responseText + "%";
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        }
        function getPressureData() {
            var url = "/getPressureData";
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("getting pressure data");
                    luminosity.innerHTML = "Pressure: " + xhr.responseText + " hPa";
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        }
        function getDistanceData() {
            var url = "/getDistanceData";
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    console.log("getting distance data");
                    distance.innerHTML = "Distance: " + xhr.responseText + " mm";
                }
            }
            xhr.open("GET", url, true);
            xhr.send();
        }
        function displaySensorsData() {
            getLuminosityData();
            getTemperatureData();
            getHumidityData();
            getDistanceData();
        }
        window.onload = function () {
            displaySensorsData() // the function fires as soon as the page is loaded
            setInterval(displaySensorsData, 5000); // the function runs again every 5 seconds
        }
    </script>
</body>
</html>
  )=====";

#endif