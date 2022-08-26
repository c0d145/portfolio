<h1>{{$heading}}</h1>

<!-- @ are so called directives and save the php start and end-tags-->
@if(count($listings) == 0)
    <p>No listing found</p>
@endif
<!-- Same functionality could be impelemted with unless, else and endunless-->

@foreach($listings as $listing)
    <h2>
        <a href="/listings/{{$listing['id']}}">{{$listing['title']}}</a>
    </h2>
    <p>{{$listing['description']}}</p>
@endforeach