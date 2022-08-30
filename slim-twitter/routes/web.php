<?php

use App\Models\Tweet;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\UserController;
use App\Http\Controllers\TweetController;

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

Route::get('/', [TweetController::class, 'index']);

// Testing the output possibilities.
Route::get('/hello', function () {
    return response('<h1>Hello World</h1>')
        ->header('Content-Type', 'text/plain')
        ->header('foo', 'bar');
});

// Testing id based route. Could become handy for showing tweets.
Route::get('/posts/{id}', function ($id) {
    return response('Posts' . $id);
})->where('id', '[0-9]+');

// Testing request handling.
Route::get('/search', function (Request $request) {
    //return response('Posts' . $id);
    dd($request);
    // dd($request->name . ' ' . $request-> city);
    //return $request->name . ' ' . $request-> city;
});

// Show all Tweets.
Route::get('/tweets', [TweetController::class, 'index']);

// Show create form
Route::get('/tweets/create', [TweetController::class, 'create'])->middleware('auth');

// Store tweet data
Route::post('/tweets', [TweetController::class, 'store'])->middleware('auth');

// Show edit form
Route::get('/tweets/{tweet}/edit', [TweetController::class, 'edit'])->middleware('auth');

// Update tweet
Route::put('/tweets/{tweet}', [TweetController::class, 'update'])->middleware('auth');

// Delete tweet
Route::delete('/tweets/{tweet}', [TweetController::class, 'destroy'])->middleware('auth');

// Manage Tweets
Route::get('/tweets/manage', [TweetController::class, 'manage'])->middleware('auth');

// Show single tweet with route model binding. -> Automatic 404 for non existing IDs.
// IMPORTANT: This must be after all other routes to /tweet/ so they are not
// interpreted as ID checks.
Route::get('/tweets/{tweet}', [TweetController::class, 'show']);

// Show register / create Form
Route::get('/register', [UserController::class, 'create'])->middleware('guest');

// Create new user
Route::post('/users', [UserController::class, 'store']);

// Log user Out
Route::post('/logout', [UserController::class, 'logout'])->middleware('auth');

// Show login form
Route::get('/login', [UserController::class, 'login'])->name('login')->middleware('guest');

// Login user
Route::post('/users/authenticate', [UserController::class, 'authenticate']);

// Route::get('/dashboard', function () {
//     return view('dashboard');
// })->middleware(['auth'])->name('dashboard');

// require __DIR__ . '/auth.php';
