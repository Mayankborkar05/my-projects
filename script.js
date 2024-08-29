const readline = require('readline');
const https = require('https');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.question('Enter the url: ', (url) => {
  fetchHTMLContent(url)
    .then((htmlContent) => {
      if (detectPhishing(htmlContent)) {
        console.log("Warning: Phishing website detected!");
      } else {
        console.log("No phishing indicators found.");
      }
      rl.close();
    })
    .catch((error) => {
      console.error("Error fetching website content:", error.message);
      rl.close();
    });
});

function fetchHTMLContent(urlString) {
  return new Promise((resolve, reject) => {
    https.get(urlString, (res) => {
      let content = '';
      res.on('data', (chunk) => {
        content += chunk;
      });
      res.on('end', () => {
        resolve(content);
      });
    }).on('error', (error) => {
      reject(error);
    });
  });
}

function detectPhishing(htmlContent) {
  // Example phishing indicator: detecting a fake login form
  const phishingPattern = /<form[^>]\baction\s=\s*"[^"]login[^"]"[^>]*>/gi;
  return phishingPattern.test(htmlContent);
}