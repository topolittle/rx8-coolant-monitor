ARG VARIANT
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

ARG ARDUINO_IDE_VERSION
ARG ARDUINO_CLI_VERSION
ARG USER_NAME

RUN apt update \
    && apt install -y \
    git \
    bash-completion

# Adds the user to the group of which the group id corresponds to the host 'dialout' group id.
# If the group id doesn't exists locally, create a new group with the right group id and add the user to it.
# Add also the 'll' alias for the user and bash completion for git.
COPY ./envfile /root/
RUN . /root/envfile \
    && rm -f /root/envfile \
    && echo "alias ll='ls -ltr'" >> /home/$USER_NAME/.bashrc \
    && echo ". /usr/share/bash-completion/completions/git" >> /home/vscode/.bashrc \
    && if grep :${DIALOUT_GID}: /etc/group; then \
        usermod -a -G $(grep :${DIALOUT_GID}: /etc/group | cut -d ':' -f 1) $USER_NAME; \
    else \
        groupadd -g ${DIALOUT_GID} vscodedialout && usermod -a -G vscodedialout $USER_NAME; \
    fi

# Install Arduino IDE
RUN mkdir -p /opt \
    && cd /opt \
    && wget https://downloads.arduino.cc/arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
    && tar -xf arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
    && rm -f arduino-${ARDUINO_IDE_VERSION}-linux64.tar.xz \
    && mv arduino-${ARDUINO_IDE_VERSION} arduino \
    && /opt/arduino/install.sh

# Install Arduino CLI
RUN mkdir -p /opt/arduino-cli \
    && cd /opt/arduino-cli \
    && wget https://github.com/arduino/arduino-cli/releases/download/${ARDUINO_CLI_VERSION}/arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && tar -xf arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && rm -f arduino-cli_${ARDUINO_CLI_VERSION}_Linux_64bit.tar.gz \
    && ln -s /opt/arduino-cli/arduino-cli /usr/local/bin/arduino-cli

# Set the default user
USER $USER_NAME

LABEL arduino-ide-version="${ARDUINO_IDE_VERSION}"
LABEL desccription="Image based on Debuan providing Arduino build and debug environment"

# Project specific section
# ========================

# Install required libraries
RUN arduino-cli lib install "Adafruit GFX Library"
RUN arduino-cli lib install "Adafruit SSD1306"
