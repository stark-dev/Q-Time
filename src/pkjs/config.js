module.exports = [
  {
    "type": "heading",
    "defaultValue": "Q-Time Configuration"
  },
  {
    "type": "text",
    "defaultValue": "Save settings and Reload your watchface in order to apply changes"
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Color settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "colors",
        "label": "Choose your color set",
        "defaultValue": "0",
        "options": [
          { 
            "label": "Default", 
            "value": "0" 
          },
          { 
            "label": "Dark", 
            "value": "1" 
          },
          { 
            "label": "Light", 
            "value": "2" 
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
        "defaultValue": "Time Settings"
      },
      {
        "type": "radiogroup",
        "messageKey": "time_format",
        "label": "Time format",
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
        "label": "Time font size",
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
        "label": "Day font size",
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
        "label": "Date font size",
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