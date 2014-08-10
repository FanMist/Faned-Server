#!/bin/sh
if [ -x ./bin_unix/sauer_faned_client ]
then
  exec ./bin_unix/sauer_faned_client -q${HOME}/.sauerbraten -gsauer_faned_log.txt "$@"
else
  echo "Your platform does not have a pre-compiled Fanatic Edition client."
  echo "Please follow the following steps to build a client:"
  echo "1) Ensure you have the SDL, SDL-image, SDL-mixer, and OpenGL libraries installed."
  echo "2) Change directory to fanatic_src/ and type \"(cd enet/; chmod +x *; cd ..; make install)\"."
  echo "3) If the build succeeds, return to this directory and run this script again."
  exit 1
fi
