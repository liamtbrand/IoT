curl --silent --location https://deb.nodesource.com/setup_6.x | sudo bash -
sudo apt-get install --yes nodejs

npm install socket.io
npm install --save express

npm install -g gulp

npm install semantic-ui --save
cd semantic/
gulp build
cd ../
