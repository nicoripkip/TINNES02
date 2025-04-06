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
const caCert = `-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----`;

// Set the options for the broker connection
const options = {
    // Clean session
    clean: true ,
    connectTimeout: 2000,
    ca: caCert,
    reconnectPeriod: 1000,
    // Authentication
    clientId: USER.key,
    debug: false,
    username: "student",
    password: 'welkom01',
    
}
const url       = "wss://netwerkenbasis.com:8884/"
const room      = "chat/message"
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
