<x-layout>
@include('partials._hero')
@include('partials._search')

<div class="lg:grid lg:grid-cols-1 gap-4 space-y-4 md:space-y-0 mx-4">

    @unless(count($tweets) == 0)
    
    @foreach($tweets as $tweet)
    <x-tweet-card :tweet="$tweet"/>
    @endforeach
    
    @else
    <p>No tweet found</p>
    @endunless
</div>
<div class="mt-6 p-4">
    {{$tweets->links()}}
</div>
</x-layout>