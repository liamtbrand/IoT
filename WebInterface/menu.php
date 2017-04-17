<style>
.column{
  max-width: 450px;
}
</style>

<div class="ui secondary pointing menu">
  <a class="item" id="home">
    <i class="home icon"></i>
    Home
  </a>
  <a class="item" id="setup">
    <i class="settings icon"></i>
    Setup
  </a>
  <a class="item" id="sharing">
    <i class="users icon"></i>
    Sharing
  </a>
  <div class="right menu">
    <a class="ui item" id="profile">
      <i class="user icon"></i>
      <div id="welcome"></div>
    </a>
    <a class="ui item" id="signout">
      <i class="sign out icon"></i>
      Sign out
    </a>
  </div>
</div>

<script>
  $(document).ready(function(){

    var name = "Liam";
    $('#welcome').html("Hello, "+name+".");

    var menu = window.location.pathname.split("/")[1];
    $('#'+menu).addClass('active');

    $('#home').click(function(){
      window.location = "/home";
    });
    $('#setup').click(function(){
      window.location = "/setup";
    });
    $('#sharing').click(function(){
      window.location = "/sharing";
    });

    $('#profile').click(function(){
      window.location = "/profile";
    });
    $('#signout').click(function(){
      window.location = "/signout";
    });

  });
</script>
