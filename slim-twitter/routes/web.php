<?php

use Illuminate\Support\Facades\Route;
use Illuminate\Http\Request;
use App\Models\Listing;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

// Testing the output possibilities.
Route::get('/hello', function() {
    return response('<h1>Hello World</h1>')
        -> header('Content-Type', 'text/plain')
        -> header('foo', 'bar');
});

// Testing id based route. Could become handy for showing tweets.
Route::get('/posts/{id}', function($id) {
    return response('Posts' . $id);
})->where('id', '[0-9]+');

// Testing request handling.
Route::get('/search', function(Request $request) {
    //return response('Posts' . $id);
    dd($request);
    // dd($request->name . ' ' . $request-> city);
    //return $request->name . ' ' . $request-> city;
});

// Show all Listings.
Route::get('/listing', function() {
    return view('listings', [
        'heading' => 'Latest Listings',
        'listings' => Listing::all()
        ]);
});

// Show single listing.
Route::get('/listings/{id}', function($id) {
    return view('listing', [
        'listing' => Listing::find($id)
        ]);
});


Route::get('/dashboard', function () {
    return view('dashboard');
})->middleware(['auth'])->name('dashboard');

require __DIR__.'/auth.php';
