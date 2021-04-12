//Anuar Saenger Gomez 
//Event system code for dynamic event handling.


class Event
{
  public:
  Event *next;
  void *finishConditionVariable;
  void *finishConditionValue;

  virtual boolean isEventRunning(void);
  virtual void doEvent();
  virtual void updateEvent();

  Event(void *finishConditionVar, void *finishContidionVal){
    next = NULL;
    
  }
  
}


class EventController
{
  private:
  Event *_currentEvent;
  Event *_nextEvent;
  Event *_endOfQueueEvent;
  public:

  EventController(){
    Event *_currentEvent = NULL;
    Event *_nextEvent = NULL;
    Event *_endOfQueueEvent = NULL;
  }
  
  void addEventToQueue(Event *eventToAdd){
    if(!_endOfQueueEvent){
      _nextEvent = eventToAdd;
      _endOfQueueEvent = eventToAdd;
    }
    else{
      _endOfQueueEvent->next = eventToAdd;
      _endOfQueueEvent = eventToAdd;
    }
//
//    else{                           // code in case endOfQueueEvent approach doesnt work.
//      Event *finalEventInLine = _nextEvent;
//      {
//        finalEventInLine = finalEventInLine->next;
//      }while (finalEventInLine->next)
//    }
//    finalEventInLine->next = eventToAdd;  
  }
}
