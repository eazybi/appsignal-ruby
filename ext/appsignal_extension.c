#include<ruby.h>

void appsignal_start(void);
void appsignal_start_transaction(char *);
void appsignal_start_event(char *);
void appsignal_finish_event(char *, char *, char *, char *);
void appsignal_set_transaction_error(char *, char *, char *);
void appsignal_set_transaction_error_data(char *, char *, char *);
void appsignal_set_transaction_basedata(char *, char *, char *, long);
void appsignal_set_transaction_metadata(char *, char *, char *);
void appsignal_finish_transaction(char *);
void appsignal_set_gauge(char *, float);
void appsignal_set_process_gauge(char *, float);
void appsignal_increment_counter(char *, int);
void appsignal_add_distribution_value(char *, float);

char * string(VALUE str) {
  // TODO we should use RSTRING_PTR and RSTRING_LEN, see:
  // https://github.com/ruby/ruby/blob/trunk/doc/extension.rdoc
  return StringValueCStr(str);
}

VALUE start(VALUE self) {
  appsignal_start();
  return Qnil;
}

VALUE start_transaction(VALUE self, VALUE transaction_id) {
  appsignal_start_transaction(string(transaction_id));
  return Qnil;
}

VALUE start_event(VALUE self, VALUE transaction_id) {
  appsignal_start_event(string(transaction_id));
  return Qnil;
}

VALUE finish_event(VALUE self, VALUE transaction_id, VALUE name, VALUE title, VALUE body) {
  appsignal_finish_event(
      string(transaction_id),
      string(name),
      string(title),
      string(body)
  );
  return Qnil;
}

VALUE set_transaction_error(VALUE self, VALUE transaction_id, VALUE name, VALUE message) {
  appsignal_set_transaction_error(
      string(transaction_id),
      string(name),
      string(message)
  );
  return Qnil;
}

VALUE set_transaction_error_data(VALUE self, VALUE transaction_id, VALUE key, VALUE payload) {
  appsignal_set_transaction_error_data(
      string(transaction_id),
      string(key),
      string(payload)
  );
  return Qnil;
}

VALUE set_transaction_basedata(VALUE self, VALUE transaction_id, VALUE namespace, VALUE action, VALUE queue_start) {
  appsignal_set_transaction_basedata(
      string(transaction_id),
      string(namespace),
      string(action),
      FIX2LONG(queue_start)
  );
  return Qnil;
}

VALUE set_transaction_metadata(VALUE self, VALUE transaction_id, VALUE key, VALUE value) {
  appsignal_set_transaction_metadata(
      string(transaction_id),
      string(key),
      string(value)
  );
  return Qnil;
}

VALUE finish_transaction(VALUE self, VALUE transaction_id) {
  appsignal_finish_transaction(string(transaction_id));
  return Qnil;
}

VALUE set_gauge(VALUE self, VALUE key, VALUE value) {
  appsignal_set_gauge(
      string(key),
      NUM2DBL(value)
  );
  return Qnil;
}

VALUE set_process_gauge(VALUE self, VALUE key, VALUE value) {
  appsignal_set_process_gauge(
      string(key),
      NUM2DBL(value)
  );
  return Qnil;
}

VALUE increment_counter(VALUE self, VALUE key, VALUE count) {
  appsignal_increment_counter(
      string(key),
      FIX2INT(count)
  );
  return Qnil;
}

VALUE add_distribution_value(VALUE self, VALUE key, VALUE value) {
  appsignal_add_distribution_value(
      string(key),
      NUM2DBL(value)
  );
  return Qnil;
}

void Init_appsignal_extension(void) {
  VALUE Appsignal = rb_define_module("Appsignal");
  VALUE Extension = rb_define_module_under(Appsignal, "Extension");

  // Transaction monitoring
  rb_define_singleton_method(Extension, "start",                      start,                      0);
  rb_define_singleton_method(Extension, "start_transaction",          start_transaction,          1);
  rb_define_singleton_method(Extension, "start_event",                start_event,                1);
  rb_define_singleton_method(Extension, "finish_event",               finish_event,               4);
  rb_define_singleton_method(Extension, "set_transaction_error",      set_transaction_error,      3);
  rb_define_singleton_method(Extension, "set_transaction_error_data", set_transaction_error_data, 3);
  rb_define_singleton_method(Extension, "set_transaction_basedata",   set_transaction_basedata,   4);
  rb_define_singleton_method(Extension, "set_transaction_metadata",   set_transaction_metadata,   3);
  rb_define_singleton_method(Extension, "finish_transaction",         finish_transaction,         1);

  // Metrics
  rb_define_singleton_method(Extension, "set_gauge",                  set_gauge,                  2);
  rb_define_singleton_method(Extension, "set_process_gauge",          set_process_gauge,          2);
  rb_define_singleton_method(Extension, "increment_counter",          increment_counter,          2);
  rb_define_singleton_method(Extension, "add_distribution_value",     add_distribution_value,     2);
}
