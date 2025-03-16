// Generate random user on startup
const t = "user".concat(crypto.randomUUID())
const username = document.getElementById("username")
const USER = {
    "key":  t,
    "name": t.substring(0, 9)
}
delete t // delete the random generated key
username.textContent = "User: ".concat(USER.name)
let messageCounter = 0


// Set the options for the broker connection
const options = {
    // Clean session
    clean: false,
    connectTimeout: 2000,
    qos: 2,
    protocol: "ws",
    // Authentication
    clientId: USER.key,
    debug: true,
    username: "niko",
    password: 'henkdepotvis',
    
}
const url       = "ws://127.0.0.1:1883/"
const room      = "chatapp"
const client    = mqtt.connect(url, options)

console.log(options.cert)
// Get the modifiable DOM elements
const box   = document.getElementById("chat-box")
const input = document.getElementById("message")
const btn   = document.getElementById("send_btn")


/**
 * Function to create an incoming chat message
 * 
 * @param {} user 
 * @param {*} message 
 */
function createMessage(user, message)
{
    const m = document.createElement("div")
    const p = document.createElement("p")

    p.className = "chat-message-text"
    p.textContent = user.concat(": ".concat(message))


    if (user === USER.name) {
        m.className = "chat-message chat-message-own"
    } else {
        m.className = "chat-message chat-message-other"
    }
    m.style.top = `${messageCounter*13}%`

    m.appendChild(p)

    box.appendChild(m)
}


/**
 * Eventlistener to connect to the broker, and subscribe to a room
 * 
 */
client.on("connect", (connack) => {
    if (connack.returnCode !== 0) {
        console.log(`Error connecting: ${connack.returnCode}`)
    } else {

    client.subscribe(room, { qos: 2 },  (error, granted) => {
        if (!error) {
            // client.publish(room, 'Henkie de henkers')
            console.log(granted)
        }
    });
    }
});


/**
 * Eventlistener to listen for new messages on the topic of the broker
 * 
 */
client.on("message", (topic, message) => {
    console.log(message.toString())
    console.log(topic)
    createMessage(message.toString().substring(0, 9), message.toString().substring(10, message.toString().length))
    messageCounter++
})


/**
 * Function to handle button events and push a message to the broker
 * 
 */
btn.onclick = () => {
    if (input.value.length > 0) {
        client.publish(room, USER.name.concat(":".concat(input.value)), { 
            retain: false, 
            qos: 2 
        })
        
        input.value = ""
    }
}
