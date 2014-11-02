Pluggable Bot
=============

This is a small bot app for instant messaging services like Gadu-Gadu (IM
protocol used mostly in Poland), XMPP etc. My goal was to make it very pluggable.
Because of that, in the core executable, there is no support for any particular
protocol and there are no commands at all. Everything is put in plugins.

Purpose
-------

This project was written as a "homework". It has no real use, but was quite
pleasant to write and allowed me to do something more than simple exercises
in school. I'm pretty happy with the final result, even though there are bugs.

This is mostly proof of what I can write. I have no plans to develop it in the
future.

Compilation and usage
----------------------------

The project was written in Visual Studio 2013 and uses C++11, so it is very
likely that it won't compile in earlier versions of VS or in G++.
Despite that, the project should compile out-of-the-box. Running it requires
specifying configuration file (`config.json`). GG plugin requires working
account that you may create on [Gadu-Gadu page](http://gg.pl).

Sample `config.json`:
```
{
    "pluginsPath": "Plugins",
    "sendJSON": false,
    "DefaultProtocols": {
        "gg": {
            "number": 0,
            "password": "pass",
            "contacts": [ ]
        }
    }
}
```

Documentation
-------------

The documentation, unfortunately, is written mostly in Polish. I don't plan
to translate it to English. However, I think that the code is quite basic
and should not be hard to understand.


License
-------
The project is under the MIT License.