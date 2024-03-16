<?php

namespace App;

use Illuminate\Database\Eloquent\Model;
use App\User;

class UserList extends Model{

    protected $table = 'userList';
    public $primaryKey = 'id';

    public function user(){
        return $this->belongsTo('App\User');
    }

    public function items(){
        return $this->hasMany('App\Post');
    }

}
