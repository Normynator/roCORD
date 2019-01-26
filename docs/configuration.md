# Configuration

## Config file
```json
{
    "version": 1,
    "debug": 0,
    "display_name": "roCORD",
    "log_level": 255,
    "token": "NDY4NTM2MTUyNjE4Njk2NzA4.Dm857g.-cRGQwoSGwhhO0ECv9V-Eo5zavA",
    "presence": "by Normynator",
    "channels" : {
        "general": "280871866669989888"
    }
}
```
Above you see the configuration file for roCORD.
#### version (int): 
specifies which config version to use. Is required in every config.
#### debug (int): 
- 0 : OFF
- 1 : ON

#### log_level (integer):
```
the log level is computed this way:
 * debug:   1
 * info:    2
 * status:  4
 * warning: 8
 * error:   12
 *
 * now you can combine any log levels like this:
 *    error, warning and status => 12 + 8 + 4 = 24
 *    so log_level would be 24.
```
#### display_name (string): 
name of the bot in your server
#### token (string): 
the token is used to connect your bot to your server. This option is required. Keep the token secret!
#### presence (string): 
text displayed below the bot name in your server
#### channels (array (string, string)): 
first string contains the ingame channel name (without #, like global, support, trade). Second argument holds the id of your discord channel where you want the messages to be.


## CA Certificate
A certificate is provided in the config folder. It is used for encrypted communication.
You can swap the provided certificate with your own trusted one.
The provided certificate was extractet from a recent Mozilla Firefox version.
