var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var s = require('net').Socket();

s.connect(8081);

app.get('/', function(req, res){
  res.sendFile(__dirname + '/home/index.html');
});
app.get('/hub.js', function(req, res){
  res.sendFile(__dirname + '/hub.js');
});
app.get('/menu.html', function(req, res){
  res.sendFile(__dirname + '/menu.html');
});
/*
app.get('/semantic/dist/semantic.min.css', function(req, res){
  res.sendFile(__dirname + '/semantic/dist/semantic.min.css');
});
app.get('/semantic/dist/semantic.min.js', function(req, res){
  res.sendFile(__dirname + '/semantic/dist/semantic.min.js');
});
*/
app.get('/semantic/dist/*', function(req, res){
  //console.log(req["url"]);
  res.sendFile(__dirname + req["url"]);
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

http.listen(80, function(){
  console.log('listening on *:80');
});
