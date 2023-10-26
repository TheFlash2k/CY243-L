FROM dperson/samba

EXPOSE 139/tcp 445/tcp

ENV USER="hodor;stark"
ENV SHARE="share;/share;yes;no;yes;all;none;none;Public"
ENV SHARE1="secure-share;/secure-share;yes;yes;no;hodor;none;none;Only the true king can access this share."

COPY ./docker-entrypoint.sh /
RUN mkdir -p /share /secure-share
RUN chmod +x /docker-entrypoint.sh

ENTRYPOINT [ "/docker-entrypoint.sh" ]