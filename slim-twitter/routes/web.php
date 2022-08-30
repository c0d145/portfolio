<?php

use App\Models\Listing;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\UserController;
use App\Http\Controllers\ListingController;

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

Route::get('/', [ListingController::class, 'index']);

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

// Show all Listings.
Route::get('/listings', [ListingController::class, 'index']);

// Show single listing.
// Route::get('/listings/{id}', function ($id) {
//     return view('listing', [
//         'listing' => Listing::find($id)
//     ]);
// });

// Show create form
Route::get('/listings/create', [ListingController::class, 'create']);

// Store listing data
Route::post('/listings', [ListingController::class, 'store']);

// Show edit form
Route::get('/listings/{listing}/edit', [ListingController::class, 'edit']);

// Update listing
Route::put('/listings/{listing}', [ListingController::class, 'update']);

// Delete listing
Route::delete('/listings/{listing}', [ListingController::class, 'destroy']);

// Show single listing with route model binding. -> Automatic 404 for non existing IDs.
// IMPORTANT: This must be after all other routes to /listing/ so they are not
// interpreted as ID checks.
Route::get('/listings/{listing}', [ListingController::class, 'show']);

// Show register / create Form
Route::get('/register', [UserController::class, 'create']);

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
