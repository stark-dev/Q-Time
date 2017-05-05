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
      },
      {
        "type": "toggle",
        "messageKey": "leading_zero",
        "label": "Show leading zero in time",
        "description": "Active 01:23, Disabled 1:23",
        "defaultValue": true
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
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Color settings"
      },
      {
        "type": "toggle",
        "messageKey": "default_colors",
        "label": "Use Default color scheme",
        "description": "Disable this option in order to set custom colors",
        "defaultValue": true
      },
      {
        "type": "radiogroup",
        "messageKey": "background_color",
        "label": "Choose background color:",
        "defaultValue": "0",
        "options": [
          { 
            "label": "Black", 
            "value": "0" 
          },
          { 
            "label": "White", 
            "value": "1" 
          }
        ]
      },
      {
        "type": "color",
        "messageKey": "time_color",
        "defaultValue": "ffffff",
        "label": "Time Color",
      },
      {
        "type": "color",
        "messageKey": "day_color",
        "defaultValue": "ffffff",
        "label": "Day Color"
      },
      {
        "type": "color",
        "messageKey": "date_color",
        "defaultValue": "ffffff",
        "label": "Date Color"
      },
      {
        "type": "color",
        "messageKey": "dial_color",
        "defaultValue": "ffffff",
        "label": "Dial Color"
      }   
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];