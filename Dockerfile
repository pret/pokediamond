FROM i386/alpine

RUN apk update
RUN apk add --no-cache build-base libpng-dev wine ncurses freetype
RUN apk add binutils-arm-none-eabi --no-cache --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted

ENV BUSYBOX 1
WORKDIR /app

CMD ["/bin/sh"]