function Hub(address,port){
  this._address = address;
  this._port = port;
}

Hub.prototype.sendMessage = function(message){
  var msg = "{\"address\":\""+this._address+"\",\"port\":\""+this._port+"\",\"data\":\""+message+"\"}";

  xmlhttp = new XMLHttpRequest();
  var url = "http://localhost:8081/";
  xmlhttp.open("POST", url, true);
  xmlhttp.onreadystatechange = function () { //Call a function when the state changes.
  if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
  cb(xmlhttp.responseText);
  }
  };
  xmlhttp.send(msg);

  console.log(msg);
};
