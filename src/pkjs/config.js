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
        "defaultValue": "48",
        "options": [
          { 
            "label": "Small", 
            "value": "44" 
          },
          { 
            "label": "Medium", 
            "value": "46" 
          },
          { 
            "label": "Large", 
            "value": "48" 
          }
        ]
      },
      {
        "type": "radiogroup",
        "messageKey": "day_font",
        "label": "Day font size",
        "defaultValue": "16",
        "options": [
          { 
            "label": "Small", 
            "value": "16" 
          },
          { 
            "label": "Medium", 
            "value": "18" 
          },
          { 
            "label": "Large", 
            "value": "20" 
          }
        ]
      },
      {
        "type": "radiogroup",
        "messageKey": "date_font",
        "label": "Date font size",
        "defaultValue": "22",
        "options": [
          { 
            "label": "Small", 
            "value": "20" 
          },
          { 
            "label": "Medium", 
            "value": "22" 
          },
          { 
            "label": "Large", 
            "value": "24" 
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