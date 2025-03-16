FROM node:latest
WORKDIR /usr/src/app

COPY package*.json ./
RUN npm install
COPY . ./

USER root
EXPOSE 80

CMD ["node", "./app/app.js"]