function Hub(address,port){
  this._address = address;
  this._port = port;
}

Hub.prototype.sendMessage = function(message){
  //var msg = "{\"address\":\""+this._address+"\",\"port\":\""+this._port+"\",\"data\":\""+message+"\"}";
  var msg = "{\"data\":\""+message+"\"}";

  $.ajax({
    method: "POST",
    url: "http://localhost:8081/",
    data: JSON.parse(msg)
  })
  .done(function( msg ) {
    console.log(msg);
  });

};
