module.exports = [
  {
    "type": "heading",
    "defaultValue": "Q-Time Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Save settings and reload your watchface in order to apply changes"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Color settings"
      },
      {
        "type": "toggle",
        "messageKey": "default_settings",
        "label": "Use Default color scheme",
        "defaultValue": true
      },
      {
        "type": "radiogroup",
        "messageKey": "background_color",
        "label": "Choose your color set:",
        "defaultValue": "0",
        "options": [
          { 
            "label": "Dark", 
            "value": "0" 
          },
          { 
            "label": "Light", 
            "value": "1" 
          }
        ]
      },
      {
        "type": "color",
        "messageKey": "time_color",
        "defaultValue": "fffffff",
        "label": "Time Color",
      },
      {
        "type": "color",
        "messageKey": "day_color",
        "defaultValue": "fffffff",
        "label": "Day Color"
      },
      {
        "type": "color",
        "messageKey": "date_color",
        "defaultValue": "fffffff",
        "label": "Date Color"
      },
      {
        "type": "color",
        "messageKey": "dial_color",
        "defaultValue": "fffffff",
        "label": "Dial Color"
      }   
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Time Settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "time_format",
        "label": "Time format:",
        "defaultValue": "0",
        "options": [
          { 
            "label": "24h", 
            "value": "0" 
          },
          { 
            "label": "12h", 
            "value": "1" 
          }
        ]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Font Settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "time_font",
        "label": "Time font size:",
        "defaultValue": "2",
        "options": [
          { 
            "label": "Small", 
            "value": "0" 
          },
          { 
            "label": "Medium", 
            "value": "1" 
          },
          { 
            "label": "Large", 
            "value": "2" 
          }
        ]
      },
      {
        "type": "radiogroup",
        "messageKey": "day_font",
        "label": "Day font size:",
        "defaultValue": "1",
        "options": [
          { 
            "label": "Small", 
            "value": "0" 
          },
          { 
            "label": "Medium", 
            "value": "1" 
          },
          { 
            "label": "Large", 
            "value": "2" 
          }
        ]
      },
      {
        "type": "radiogroup",
        "messageKey": "date_font",
        "label": "Date font size:",
        "defaultValue": "1",
        "options": [
          { 
            "label": "Small", 
            "value": "0" 
          },
          { 
            "label": "Medium", 
            "value": "1" 
          },
          { 
            "label": "Large", 
            "value": "2" 
          }
        ]
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];