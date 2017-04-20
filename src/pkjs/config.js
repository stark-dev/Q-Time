module.exports = [
  {
    "type": "heading",
    "defaultValue": "Q-Time Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Customize your watchface and save changes!"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "color",
        "messageKey": "background_color",
        "defaultValue": "0x000000",
        "label": "Background Color"
      },
      {
        "type": "color",
        "messageKey": "text_color",
        "defaultValue": "0xFBD83E",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "day_color",
        "defaultValue": "0x00C4B9",
        "label": "Day Color"
      },
      {
        "type": "color",
        "messageKey": "date_color",
        "defaultValue": "0xFFFFFF",
        "label": "Date Color"
      },
      {
        "type": "color",
        "messageKey": "dial_color",
        "defaultValue": "0xFFFFFF",
        "label": "Dial Color"
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "More Settings"
      },
      {
        "type": "toggle",
        "messageKey": "default_settings",
        "label": "Use default settings",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];