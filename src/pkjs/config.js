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
        "defaultValue": "Custom/default settings"
      },
      {
        "type": "text",
        "defaultValue": "Select custom settings to make changes effective"
      },
      {
        "type": "toggle",
        "messageKey": "default_settings",
        "label": "Use default settings",
        "defaultValue": true
      },
    ]
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
        "type": "radiogroup",
        "messageKey": "time_format",
        "label": "Time format",
        "defaultValue": "24",
        "options": [
          { 
            "label": "24h", 
            "value": "24" 
          },
          { 
            "label": "12h", 
            "value": "12" 
          }
        ]
      },
      {
        "type": "slider",
        "messageKey": "time_font_size",
        "defaultValue": 3,
        "label": "Time font size",
        "description": "Select font size for time",
        "min": 1,
        "max": 3,
        "step": 1
      },
      {
        "type": "slider",
        "messageKey": "day_font_size",
        "defaultValue": 1,
        "label": "Day font size",
        "description": "Select font size for day",
        "min": 1,
        "max": 3,
        "step": 1
      },
      {
        "type": "slider",
        "messageKey": "date_font_size",
        "defaultValue": 2,
        "label": "Date font size",
        "description": "Select font size for date",
        "min": 1,
        "max": 3,
        "step": 1
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];