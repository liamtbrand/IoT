var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var s = require('net').Socket();

s.connect(8081);

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  console.log('a user connected');

  socket.on('message', function(msg){
    console.log('message: ' + msg);
    s.write(msg+"\n");
  });

  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
