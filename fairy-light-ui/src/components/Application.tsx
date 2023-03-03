import React from 'react';
import './Application.scss';
import { Slider } from './Slider/Slider';

export const Application = () => {
  document.body.classList.add('dark-mode');
  let pin = 0;

  return (
    <div id='erwt'>
      <div className='header'>
        <div className='main-heading'>
          <h1 className='themed'>Fairy Light Controller</h1>
        </div>
        <Slider pin={++pin} sync={false} />
        <Slider pin={++pin} sync={false} />
        <Slider pin={++pin} sync={false} />
        <Slider pin={++pin} sync={false} />
      </div>
    </div>
  );
};
