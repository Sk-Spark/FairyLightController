
      #ifndef main_css_H
      #define main_css_H
      const char main_css[] PROGMEM = R"rawliteral(
          :root{--app-accent-color: #32639f;--app-font-size: 16px;--app-font-family: system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Oxygen, Ubuntu, Cantarell, "Open Sans", "Helvetica Neue", sans-serif;--app-bgcolor: #202020;--app-border-color: #3b3f44;--scroll-width: 10px;--scroll-track-bgcolor: #2f2f2f52;--scroll-thumb-bgcolor: rgba(59, 59, 59, 0.747);--scroll-thumb-hover-bgcolor: #555;--selection-bgcolor: var(--app-accent-color);--selection-color: #fff;--button-color: #fff;--button-border: 1px solid #222424;--button-bgcolor: hsl(0, 0%, 22%);--button-hover-bgcolor: hsl(0, 0%, 24%);--button-active-bgcolor: hsl(0deg 0% 20%);--button-shadow-color: #00000078;--titlebar-bgcolor: hsl(0deg 0% 10%);--titlebar-color: hsl(0, 0%, 85%);--titlebar-title-color: hsl(0, 0%, 85%);--titlebar-menu-border-color: #2d2c2c;--titlebar-menu-title-hover-bgcolor: hsl(0deg 0% 12%);--titlebar-menu-title-active-bgcolor: hsl(0deg 0% 14%);--titlebar-menu-title-active-border-color: var(--titlebar-menu-border-color);--titlebar-menu-separator-bgcolor: var(--titlebar-menu-border-color);--titlebar-popup-bgcolor: hsl(0deg 0% 14%);--titlebar-popup-border: 1px solid var(--titlebar-menu-border-color);--titlebar-popup-shadow: 4px 10px 10px rgba(0, 0, 0, 0.2);--titlebar-popup-item-name-color: hsl(0, 0%, 75%);--titlebar-popup-item-shortcut-color: hsla(0, 0%, 55%, 0.8);--titlebar-popup-item-hover-color: hsl(0, 0%, 85%);--titlebar-popup-item-hover-bgcolor: hsl(0deg 0% 18%);--titlebar-popup-item-hover-shortcut-color: var(--app-accent-color);--titlebar-popup-item-name-shadow-color: #151515;--erwt-bgcolor: #262626;--erwt-heading-color: #dddddd}body:not(.dark-mode){--app-accent-color: #2f77ca;--app-bgcolor: #f1f0f0;--selection-bgcolor: var(--app-accent-color);--selection-color: #fff;--scroll-track-bgcolor: #2f2f2f1f;--scroll-thumb-bgcolor: rgb(59 59 59 / 30%);--scroll-thumb-hover-bgcolor: var(--app-accent-color);--button-border: 1px solid #eaeaea;--button-bgcolor: #fff;--button-color: #424242;--button-shadow-color: white;--button-hover-bgcolor: hsl(0, 0%, 98%);--button-active-bgcolor: hsl(0, 0%, 96%);--titlebar-bgcolor: #dcddde;--titlebar-color: #1f1f1f;--titlebar-title-color: var(--titlebar-color);--titlebar-menu-title-hover-bgcolor: #e6e6e6;--titlebar-popup-item-hover-bgcolor: hsl(210deg 16% 92%);--titlebar-popup-bgcolor: hsl(0deg 0% 99%);--titlebar-menu-title-active-bgcolor: hsl(0deg 0% 99%);--titlebar-menu-title-active-border-color: #d3d6d8;--titlebar-popup-border: 1px solid #d3d6d8;--titlebar-menu-separator-bgcolor: #d3d6d8;--titlebar-popup-item-hover-bgcolor: #d6dade;--titlebar-popup-item-name-color: #0e0e0e;--titlebar-popup-item-name-shadow-color: rgba(255, 255, 255, 0.8);--titlebar-popup-item-hover-color: #000000;--titlebar-popup-item-hover-shortcut-color: var(--app-accent-color);--titlebar-popup-item-hover-bgcolor: #e6e6e6;--erwt-bgcolor: #f8f8f8;--erwt-heading-color: #282828}body:not(.dark-mode) .main-teaser{background:#fff;color:#747474}body:not(.dark-mode) .main-teaser:after{box-shadow:none}body:not(.dark-mode) .versions .item{color:#656565;background:#fff;box-shadow:0 2px 4px rgba(0,0,0,.0196078431)}body:not(.dark-mode) .versions .item>span{color:#999}::selection{background:var(--selection-bgcolor);color:var(--selection-color)}::-webkit-scrollbar{width:var(--scroll-width)}::-webkit-scrollbar-track{background:var(--scroll-track-bgcolor)}::-webkit-scrollbar-thumb{background:var(--scroll-thumb-bgcolor)}::-webkit-scrollbar-thumb:hover{background:var(--scroll-thumb-hover-bgcolor)}html,body,#app{height:100%}body{margin:0;font-size:var(--app-font-size);font-family:var(--app-font-family);color:var(--app-color);background:var(--app-bgcolor);line-height:1.5}h1{margin:0}#app{display:flex;flex-direction:column;box-sizing:border-box;user-select:none;align-items:center;justify-content:center}#app.has-border{border:var(--app-border-color)}.rotate{animation:rotate 4.5s linear infinite}@keyframes rotate{to{transform:rotate(360deg)}}.main-heading{display:flex;align-items:center;justify-content:center;margin-bottom:3rem}.main-heading img{margin-right:1rem}.main-heading h1{font-size:1.5rem;font-weight:300;color:var(--erwt-heading-color);line-height:1;text-transform:uppercase}.hidden{display:none !important}.center{text-align:center}.main-teaser{position:relative;display:flex;line-height:25px;font-size:15px;color:gray;width:70%;margin:0 auto;margin-bottom:3rem;text-align:center;padding-left:1rem;background:#191919;padding-top:1rem;padding-bottom:10px;padding-right:1rem;border-radius:0 0 8px 8px;box-shadow:0 8px 10px 0px rgba(0,0,0,0.0117647059)}.main-teaser:after{content:"";position:absolute;top:0;width:calc(100% + 40px);height:2px;background:var(--app-accent-color);left:-20px;box-shadow:0 10px 20px rgba(0,0,0,.8901960784);border-radius:8px}.versions{display:flex;justify-content:space-between;gap:1rem;flex-wrap:wrap;border-radius:10px;box-shadow:0 0 20px inset rgba(0,0,0,.03);width:70%;margin:0 auto}.versions .item{background:#1c1c1c;color:#d1d1d1;width:calc(33.33% - 1rem);padding:4px 12px;display:flex;justify-content:space-between;font-size:14px;margin:0;box-sizing:border-box;border-radius:4px}.versions .item>*{display:flex;align-items:center}.versions .item-icon{width:16px;height:16px;margin-right:10px;opacity:.8}.versions .item>span{color:gray;text-align:right}#erwt{display:flex;flex-direction:column;max-height:800px;justify-content:space-between;background:var(--erwt-bgcolor);margin:0 auto;border-radius:10px;box-shadow:0 0 20px 4px rgba(0,0,0,0)}#erwt .header{padding:3rem 2rem 0rem 2rem;max-width:700px;width:80vw;margin:0 auto}#erwt .footer{margin-top:1rem;padding:2rem;background:var(--app-footer-bgColor)}
.field-title{transform:translateY(-50%);font-weight:500;color:rgba(255,255,255,.94);text-transform:uppercase;font-size:1rem;pointer-events:none;user-select:none;margin-top:23px;padding-left:15px}.range__slider{position:relative;width:100%;height:calc(65px - 10px);display:flex;justify-content:center;align-items:center;background:#0a0a0a;border-radius:8px;margin-bottom:2rem;padding:0px 10px}.range__slider::before,.range__slider::after{position:absolute;color:#fff;font-size:.9rem;font-weight:bold}.range__slider::before{content:attr(data-min);left:10px}.range__slider::after{content:attr(data-max);right:10px}.range__slider .length__title::after{content:attr(data-length);position:absolute;right:-16px;font-variant-numeric:tabular-nums;color:#fff}.slider{-webkit-appearance:none;width:calc(100% - (70px));height:2px;border-radius:5px;background:rgba(255,255,255,.314);outline:none;padding:0;margin:0;cursor:pointer;transition:all 2s ease-in-out}.slider::-webkit-slider-thumb{-webkit-appearance:none;width:20px;height:20px;border-radius:50%;background:#fff;cursor:pointer;transition:all .15s ease-in-out}.slider::-webkit-slider-thumb:hover{background:#d4d4d4;transform:scale(1.2)}.slider::-moz-range-thumb{width:20px;height:20px;border:0;border-radius:50%;background:#fff;cursor:pointer;transition:background .15s ease-in-out}.slider::-moz-range-thumb:hover{background:#d4d4d4}.slider_btn{background:var(--button-bgcolor);color:var(--button-color);font-weight:normal;text-shadow:0px 1px var(--button-shadow-color);font-family:var(--app-font-family);border:var(--button-border);padding:.5rem 1rem;border-radius:6px;font-size:.875rem;cursor:pointer;display:inline-flex;justify-content:space-around;align-items:center;outline:none;margin-right:5px}.slider_btn:hover{background:var(--button-hover-bgcolor)}.slider_btn:active{background:var(--button-active-bgcolor)}.slider_btn>span{color:var(--button-badge-color);background-color:var(--button-badge-bgcolor);font-size:12px;width:24px;height:24px;border-radius:50%;display:inline-flex;align-items:center;justify-content:center;display:none}.slider_btn img{width:22px;opacity:.8}

          )rawliteral";
          #endif
      