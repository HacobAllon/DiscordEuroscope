# DiscordEuroscope 1.2
A plugin written to provide discord rich presence feature for our lovely EuroScope.
And the good news is that it supports both ES *3.1d* and *3.2*!

All you need is to *load the plugin*, and it'll work!
You can download the plugin from the Releases page. Or compile it yourself using Visual Studio.

**Please** report any bugs in the issues section of this repository.

# Radio Callsigns file example:
```
MNL_CTR Manila Control
```

# Using the plugin on Mac or Linux (Wine)
EuroScope runs under Wine, but Discord runs as a normal Mac or Linux app. Wine can't connect the two on its own, so you need a small free bridge program called [rpc-bridge](https://github.com/EnderIce2/rpc-bridge). You only have to set it up once per Wine prefix (or CrossOver bottle).

When the plugin loads under Wine, it checks for the bridge. If it can't find it, it shows `... Discord can't be reached from Wine on its own ...` in EuroScope, which means the bridge isn't running yet. Follow the steps below. If everything is fine it stays quiet; type `.discord hotreload` if you want to see `Running under Wine ... Discord bridge found.`

## Mac
1. Download the latest release from the [rpc-bridge releases page](https://github.com/EnderIce2/rpc-bridge/releases) and unzip it.
2. Open Terminal in the unzipped folder and run:
   ```
   chmod +x launchd.sh
   ./launchd.sh install
   ```
3. Run `bridge.exe` with the same Wine prefix / CrossOver bottle you use for EuroScope, and click **Install**.
4. Open the Discord app, start EuroScope, and connect. If EuroScope was already open, type `.discord hotreload`.

## Linux
1. Download the latest release from the [rpc-bridge releases page](https://github.com/EnderIce2/rpc-bridge/releases) and unzip it.
2. Run `bridge.exe` with the same Wine prefix you use for EuroScope (for Lutris: *Run EXE inside Wine prefix*), and click **Install**.
3. Open the Discord app, start EuroScope, and connect. If EuroScope was already open, type `.discord hotreload`.

If you use the Flatpak version of Discord, it also needs permission to share its connection. Run this once:
```
flatpak override --user --filesystem=xdg-run/discord-ipc-0 --filesystem=xdg-run/.flatpak/com.discordapp.Discord:create com.discordapp.Discord
```

To uninstall, run `bridge.exe` again and click **Remove** (on Mac, also run `./launchd.sh remove`).

# Posting ATC chat to a Discord channel
The plugin can forward messages from the EuroScope ATC chat to a Discord channel, using a webhook. Only ATC chat is posted. Frequency chat, private messages, broadcasts and server messages are never sent. The plugin doesn't post anything on its own when it starts or connects.

1. In Discord, open the channel's settings → **Integrations** → **Webhooks** → **New Webhook**, then click **Copy Webhook URL**.
2. Open `DiscordEuroscope_config.json` (next to the plugin DLL) and paste the URL into `webhook` → `url`.
3. In EuroScope, type `.discord hotreload` to load the change. If you want to check it works, type `.discord webhooktest` to send a test message.

Notes:
- Keep your webhook URL private. Anyone who has it can post to the channel.
- Messages are posted under your callsign, as `**SENDER:** message`. Several messages that arrive close together are combined into one post.
- Messages never ping anyone, even if they contain `@everyone` or a mention.
- If your config file was made by an older version, add this section yourself, or delete the file and restart EuroScope so it's made again:
```json
"webhook": {
    "url": ""
},
```
