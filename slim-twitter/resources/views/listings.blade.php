@extends('layout')

@section('content')
@include('partials._hero')
@include('partials._search')

<div class="lg:grid lg:grid-cols-2 gap-4 space-y-4 md:space-y-0 mx-4">

<!-- @ are so called directives and save the php start and end-tags-->
@if(count($listings) == 0)
    <p>No listing found</p>
@endif
<!-- Same functionality could be impelemted with unless, else and endunless-->
</div>

@foreach($listings as $listing)
    <x-listing-card :listing="$listing"/>
@endforeach

@endsection