<?php

namespace App;

use Illuminate\Database\Eloquent\Model;
use App\PostsList;

class Item extends Model{

    protected $table = 'items';
    public $primaryKey = 'id';

    public function userList(){
        return $this->belongsTo('App\UserList');
    }
}
