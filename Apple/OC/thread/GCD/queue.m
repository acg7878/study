#import <Foundation/Foundation.h>

int main() {
  dispatch_queue_t seriaQueue =
      dispatch_queue_create("serialQueue", DISPATCH_QUEUE_SERIAL);
  dispatch_queue_t concureentQueue =
      dispatch_queue_create("concureentQueue", DISPATCH_QUEUE_CONCURRENT);

  dispatch_queue_t mainQueue = dispatch_get_main_queue();
  dispatch_queue_t globalQueue =
      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
}