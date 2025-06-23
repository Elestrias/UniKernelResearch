FROM gcc:13.2.0-bookworm AS build

WORKDIR /src

COPY ./main.c /src/main.c
COPY ../utils.c /src/utils.c

RUN set -xe; \
    gcc \
	-Wall -Wextra \
	-fPIC -pie \
	-o /main main.c utils.c \
	-O2

FROM scratch

COPY --from=build /lib/x86_64-linux-gnu/libc.so.6 /lib/x86_64-linux-gnu/libc.so.6
COPY --from=build /lib/x86_64-linux-gnu/libm.so.6 /lib/x86_64-linux-gnu/libm.so.6
COPY --from=build /lib/x86_64-linux-gnu/libpthread.so.0 /lib/x86_64-linux-gnu/libpthread.so.0
COPY --from=build /lib64/ld-linux-x86-64.so.2 /lib64/ld-linux-x86-64.so.2

COPY --from=build /main /main
