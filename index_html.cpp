#include <pgmspace.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Fairy Lights Controller</title>
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        text-align: center;
      }
      h2 {
        font-size: 1.5rem;
      }
      p {
        font-size: 1rem;
      }
      body {
        display: flex;
        flex-direction: column;
        align-items: center;
      }
      .slider {
        margin: 14px;
        width: 100%;
        height: 2vh;
        max-height: 10px;
        background: #ffd65c;
        outline: none;
        transition: opacity 0.2s;
      }
      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 20px;
        height: 4vh;
        max-height: 20px;
        background: #003249;
        cursor: pointer;
      }
      .slider::-moz-range-thumb {
        width: 35px;
        height: 25px;
        background: #003249;
        cursor: pointer;
      }
      .fairy-light-div {
        display: flex;
        align-items: center;
        padding: 5px 20px;
        border: 1px solid #3db13d;
        border-radius: 10px;
        box-shadow: 0px 0px 5px 0px green;
        width: 80vw;
        flex-direction: column;
        max-width: 500px;
        margin: 20px 0px;
      }
      .button {
        color: #fcfffc;
        background: #22aeed;
        border: 0px;
        padding: 8px;
        font-size: 16px;
        font-weight: 600;
        border-radius: 7px;
      }
      .button:hover {
        background: #0f92cd;
        cursor: pointer;
      }
      .button:active {
        cursor: pointer;
        box-shadow: 0px 0px 5px 0px #424242;
      }
      .pin_label{
        font-size: 20px;
        margin-right: 20px;
        padding-right: 10px;
        border-right: 1px solid gray;
      }
      .slider-div{
        display: flex;
        border: 1px solid grey;
        border-radius: 10px;
        margin: 11px 0px;
        padding: 0px 15px;
        align-items: center;
        width: 90%;
        justify-content: space-between;
      }
    </style>
  </head>
  <body>
    <h2>Fairy Lights Controller</h2>
    <div class="fairy-light-div">
      <div class="pin-div">
        <label class="pin_label">Pin 1</label>
        <input type="button" class="button" value="ON / OFF" onclick="btnClicked(1)" />
      </div>
      <div class="slider-div">
        <input type="range" id="pwmSlider_pin_1" min="0" max="250" step="10"
            class="slider" pin_value="1" 
        />
        <p><span id="textSliderValue_pin_1">NaNa</span></p>
      </div>
    </div>

    <div class="fairy-light-div">
      <div class="pin-div">
        <label class="pin_label">Pin 2</label>
        <input type="button" class="button" value="ON / OFF" onclick="btnClicked(2)" />
      </div>
      <div class="slider-div">
        <input type="range" id="pwmSlider_pin_2" min="0" max="250" step="10"
            class="slider" pin_value="2" 
        />
        <p><span id="textSliderValue_pin_2">NaNa</span></p>
      </div>
    </div>

    <script>
      const updateSlider = (event) => {
        const pin = event.target.attributes.pin_value.value
        const value = event.target.value;
        document.querySelector("#textSliderValue_pin_"+pin).textContent = value;
        console.log('#1 Pin:',pin,'\n Value:',value);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", `/slider?pin=${pin}&value=${event.target.value}`, true);
        xhr.send();
      };

      const slider_pin_1 = document.querySelector("#pwmSlider_pin_1");
      const  value_pin_1 = document.querySelector("#textSliderValue_pin_1");
      value_pin_1.textContent = slider_pin_1.value;
      slider_pin_1.addEventListener("input", updateSlider);
      
      const slider_pin_2 = document.querySelector("#pwmSlider_pin_2");
      const  value_pin_2 = document.querySelector("#textSliderValue_pin_2");
      value_pin_2.textContent = slider_pin_2.value;
      slider_pin_2.addEventListener("input", updateSlider);

      function btnClicked(pin) {
        var sliderValue = document.getElementById("pwmSlider_pin_"+pin).value;
        document.getElementById("textSliderValue_pin_"+pin).innerHTML = sliderValue;
        console.log('#1 Pin:',pin);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", `/toggle?pin=${pin}`, true);
        xhr.send();
      }
      
    </script>
  </body>
</html>
)rawliteral";

