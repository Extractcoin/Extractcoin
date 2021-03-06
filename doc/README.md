Extractcoin Core 0.10
=====================

Setup
---------------------
[Extractcoin Core](http://extractcoin.org/) is the original Extractcoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Extractcoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once. If you would like the process to go faster you can [download the blockchain directly](bootstrap.md).

Build Quickstart
----------------

See the quickstart guide to compile on Debian/Ubuntu [here](build-quickstart.md).

Running
---------------------
The following are some helpful notes on how to run Bitcoin on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Extractcoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/extractcoin-qt (GUI, 32-bit) or bin/32/extractcoind (headless, 32-bit)
- bin/64/extractcoin-qt (GUI, 64-bit) or bin/64/extractcoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run extractcoin-qt.exe.

### OSX

Drag Extractcoin-Qt to your applications folder, and then run Extractcoin-Qt.

### Need Help?

* Ask for help on [#extractcoin](http://webchat.freenode.net?channels=extractcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=extractcoin).

Building
---------------------
The following are developer notes on how to build Extractcoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)

Development
---------------------
The Extractcoin repo's [root README](https://github.com/extractcoin/extractcoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Coding Guidelines](coding.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Unit Tests](unit-tests.md)

### Resources
* Discuss on [#extractcoin-dev](http://webchat.freenode.net/?channels=extractcoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=extractcoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
