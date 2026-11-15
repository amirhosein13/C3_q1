// node make_pdf.js in.html out.pdf   (uses the pre-installed Playwright Chromium)
const { chromium } = require('playwright');
(async () => {
  const b = await chromium.launch();
  const p = await b.newPage();
  await p.goto('file://' + require('path').resolve(process.argv[2]));
  await p.pdf({ path: process.argv[3], format: 'A4', margin: { top: '18mm', bottom: '18mm', left: '16mm', right: '16mm' }, printBackground: true });
  await b.close();
})();
