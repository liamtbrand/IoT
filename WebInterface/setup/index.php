<?php
require '../includes.php';
require '../menu.php';
?>

<div class="ui container">
<div class="ui grid">
  <div class="four wide column">
    <div class="ui vertical pointing menu">
      <a class="item active">
        <i class="sitemap icon"></i>
        Network
      </a>
      <a class="item">
        <i class="disk outline icon"></i>
        Hubs
      </a>
      <a class="item">
        <i class="bullseye icon"></i>
        Nodes
      </a>
      <a class="item">
      </a>
      <a class="item">
        <i class="cubes icon"></i>
        Control Groups
      </a>
    </div>
  </div>
  <div class="twelve wide stretched column">
    <div class="ui segment">
      <div class="ui top attached menu">
        <div class="ui dropdown icon item">
          <i class="wrench icon"></i>
          <div class="menu">
            <div class="item">
              <i class="dropdown icon"></i>
              <span class="text">New</span>
              <div class="menu">
                <div class="item">Hub</div>
                <div class="item">Image</div>
              </div>
            </div>
            <div class="item">
              Open...
            </div>
            <div class="item">
              Save...
            </div>
            <div class="item">Edit Permissions</div>
            <div class="divider"></div>
            <div class="header">
              Export
            </div>
            <div class="item">
              Share...
            </div>
          </div>
        </div>
        <div class="right menu">
          <div class="ui right aligned category search item">
            <div class="ui transparent icon input">
              <input class="prompt" placeholder="Search animals..." type="text">
              <i class="search link icon"></i>
            </div>
            <div class="results"></div>
          </div>
        </div>
      </div>
      <div class="ui bottom attached segment">
        <p></p>
      </div>
    </div>
  </div>
</div>
</div>
