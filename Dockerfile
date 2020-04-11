FROM alpine AS builder

RUN apk update \
    && apk add build-base cmake ninja

WORKDIR /app
COPY . .
RUN ./scripts/release.sh

FROM scratch

WORKDIR /app
COPY --from=builder /app/release/rocker .
ENTRYPOINT [ "./rocker" ]
