module.exports = [
  {
    "type": "heading",
    "defaultValue": "App Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Here is some introductory text."
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
        "defaultValue": "0xFFFFFF",
        "label": "Text Color"
      },
      {
        "type": "color",
        "messageKey": "day_color",
        "defaultValue": "0xFFFFFF",
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
      },
      {
        "type": "toggle",
        "messageKey": "h12_24",
        "label": "12/24 h format",
        "defaultValue": false
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];