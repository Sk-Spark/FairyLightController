const axios = require('axios');

export const updateSlider = (url: string, value: number, pin: number) => {
  axios
    .get(`/slider?pin=${pin}&value=${value}`)
    .then((resp: any) => {
      console.log(resp.data);
    })
    .catch((err: any) => {
      console.error('ERROR:', err);
    });
};
