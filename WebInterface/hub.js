function Hub(address,port){
  this._address = address;
  this._port = port;
}

Hub.prototype.sendMessage = function(message){
  var msg = "{\"address\":\""+this._address+"\",\"port\":\""+this._port+"\",\"data\":\""+message+"\"}";
  console.log(msg);
};
