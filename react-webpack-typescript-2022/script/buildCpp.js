// Node.js program to demonstrate
// the fs.readFile() method
  
// Include fs module
const fs = require('fs');
const copyFromDir = './dist';
const files = ['main.js','index.html','main.css'];
// const copyToDir = 'buildCpp';
const copyToDir = '../';

files.forEach(file=>{
    // Use fs.readFile() method to read the file
    fs.readFile(copyFromDir+'/'+file, 'utf8', function(err, data){
        console.log(data);
        const filename = file.replace('.','_')
        const headerFilename = filename + '_H';
        const payload = `
        #ifndef ${headerFilename}
        #define ${headerFilename}
        
        const char index_html[] PROGMEM = R"rawliteral(
            ${data}
            )rawliteral";

            #endif
        `;

        fs.writeFile(copyToDir+'/'+filename+'.h', payload, (err)=>{
            if(err)
                console.log(err);
        });
    });
});
  
console.log('readFile called');